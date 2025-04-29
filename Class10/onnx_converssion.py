# convert_to_onnx.py
import torch
from model import TinyModel
import numpy as np

# Load the trained model
model = TinyModel()
model.load_state_dict(torch.load("tiny_sine_model.pth", weights_only=True))
model.eval()

# Export to ONNX with static input shape
dummy_input = torch.randn(1, 1).float()  # Input shape: [batch_size, input_dim]
dummy_input = torch.randn(1, 1).float()
torch.onnx.export(
    model,
    dummy_input,
    "quantized_sine.onnx",
    input_names=["input"],
    output_names=["output"],
    dynamic_axes={},
    opset_version=16,
    operator_export_type=torch.onnx.OperatorExportTypes.ONNX_ATEN_FALLBACK,
    do_constant_folding=True
)