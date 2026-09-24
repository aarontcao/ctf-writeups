"""
Build many KV cache blobs in one process, so the model loads once.

Input json: {"contexts": ["...", ...]}
Output dir gets <index>.b64 plus an index.json with digests and token counts.
Run inside the challenge image so the fp32 forward matches the server.
"""
import base64, hashlib, json, os, sys
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


def main(req_path, out_dir):
    contexts = json.load(open(req_path))["contexts"]
    os.makedirs(out_dir, exist_ok=True)
    tok = AutoTokenizer.from_pretrained(SOURCE, revision=REV)
    model = AutoModelForCausalLM.from_pretrained(SOURCE, revision=REV,
                                                 torch_dtype=torch.float32).to("cpu")
    model.eval()
    index = []
    for i, ctx in enumerate(contexts):
        enc = tok(ctx + TERM, return_tensors="pt", add_special_tokens=False)
        with torch.inference_mode():
            out = model(input_ids=enc.input_ids, use_cache=True)
        tensors = {}
        for layer, (k, v) in enumerate(out.past_key_values.to_legacy_cache()):
            tensors[f"layers.{layer}.key"] = k.detach().cpu().contiguous()
            tensors[f"layers.{layer}.value"] = v.detach().cpu().contiguous()
        blob = base64.b64encode(save(tensors)).decode()
        open(os.path.join(out_dir, f"{i}.b64"), "w").write(blob)
        index.append({"i": i, "context": ctx, "tokens": int(enc.input_ids.shape[-1]),
                      "digest": tensor_digest(load(base64.b64decode(blob)))})
        print(i, index[-1]["tokens"], index[-1]["digest"], flush=True)
    json.dump(index, open(os.path.join(out_dir, "index.json"), "w"), ensure_ascii=False)


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
