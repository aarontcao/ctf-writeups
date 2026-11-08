# Build a base64 safetensors KV-cache blob for a given context string.
# Must run inside the challenge image so the fp32 forward matches bit for bit.
import os, sys, base64, json, hashlib
import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
from safetensors.torch import save, load

torch.set_num_threads(int(os.getenv("TORCH_THREADS", "4")))
try:
    torch.set_num_interop_threads(1)
except Exception:
    pass

SOURCE = os.getenv("SOURCE_MODEL", "Qwen/Qwen2.5-0.5B-Instruct")
REV = os.getenv("SOURCE_REVISION", "7ae557604adf67be50417f59c2c2f167def9a775")
TERM = "\n[END HANDOFF]"

def tensor_digest(tensors):
    d = hashlib.sha256()
    for name in sorted(tensors):
        t = tensors[name].detach().cpu().contiguous()
        d.update(name.encode()); d.update(str(tuple(t.shape)).encode()); d.update(t.numpy().tobytes())
    return d.hexdigest()

def build(ctx=None, ids=None):
    tok = AutoTokenizer.from_pretrained(SOURCE, revision=REV)
    model = AutoModelForCausalLM.from_pretrained(SOURCE, revision=REV, torch_dtype=torch.float32).to("cpu")
    model.eval()
    if ids is None:
        enc = tok(ctx + TERM, return_tensors="pt", add_special_tokens=False)
        input_ids = enc.input_ids
    else:
        input_ids = torch.tensor([ids])
    with torch.inference_mode():
        out = model(input_ids=input_ids, use_cache=True)
    tensors = {}
    for layer, (k, v) in enumerate(out.past_key_values.to_legacy_cache()):
        tensors[f"layers.{layer}.key"] = k.detach().cpu().contiguous()
        tensors[f"layers.{layer}.value"] = v.detach().cpu().contiguous()
    blob = base64.b64encode(save(tensors)).decode()
    rt = load(base64.b64decode(blob))
    return blob, tensor_digest(rt), input_ids.shape[-1]

if __name__ == "__main__":
    payload = json.load(open(sys.argv[1]))
    blob, dig, n = build(payload.get("context"), payload.get("ids"))
    json.dump({"blob": blob, "digest": dig, "tokens": n}, open(sys.argv[2], "w"))
    print("tokens", n, "digest", dig)
