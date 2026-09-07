const form = document.querySelector("#upload-form");
const input = document.querySelector("#activity");
const dropzone = document.querySelector("#dropzone");
const fileName = document.querySelector("#file-name");
const button = document.querySelector("#submit-button");
const result = document.querySelector("#result");

function choose(file) {
  if (!file) return;
  const extension = file.name.toLowerCase().endsWith(".pka");
  if (!extension) {
    input.value = "";
    button.disabled = true;
    fileName.textContent = "Choose a saved .pka";
    result.className = "result error";
    result.textContent = "Only Cisco Packet Tracer .pka activities can be relayed.";
    return;
  }
  fileName.textContent = `${file.name} · ${(file.size / 1024 / 1024).toFixed(2)} MiB`;
  button.disabled = file.size > 8 * 1024 * 1024;
  result.className = "result";
  result.textContent = button.disabled ? "This file exceeds the 8 MiB relay limit." : "Activity staged. Ready to transmit.";
}

input.addEventListener("change", () => choose(input.files[0]));
["dragenter", "dragover"].forEach((event) => dropzone.addEventListener(event, (e) => { e.preventDefault(); dropzone.classList.add("dragging"); }));
["dragleave", "drop"].forEach((event) => dropzone.addEventListener(event, (e) => { e.preventDefault(); dropzone.classList.remove("dragging"); }));
dropzone.addEventListener("drop", (event) => {
  const [file] = event.dataTransfer.files;
  if (!file) return;
  const transfer = new DataTransfer();
  transfer.items.add(file);
  input.files = transfer.files;
  choose(file);
});

form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const [file] = input.files;
  if (!file || button.disabled) return;
  button.disabled = true;
  result.className = "result";
  result.textContent = "Decrypting activity and checking the relay state…";
  try {
    const response = await fetch("/api/submit", { method: "POST", headers: { "content-type": "application/octet-stream" }, body: file });
    const body = await response.json();
    result.className = `result ${body.ok ? "success" : "error"}`;
    result.textContent = body.message || "Verifier returned no status.";
    if (body.flag) {
      const flag = document.createElement("span");
      flag.className = "flag";
      flag.textContent = body.flag;
      result.append(flag);
    }
  } catch {
    result.className = "result error";
    result.textContent = "The relay is unavailable. Try again shortly.";
  } finally {
    button.disabled = false;
  }
});
