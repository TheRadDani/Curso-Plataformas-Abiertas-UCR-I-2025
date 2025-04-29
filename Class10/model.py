import torch
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt

class TinyModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.fc1 = nn.Linear(1, 6)
        self.fc2 = nn.Linear(6, 4)
        self.fc3 = nn.Linear(4, 1)
        self.act = nn.ReLU6()

    def forward(self, x):
        x = self.act(self.fc1(x))
        x = self.act(self.fc2(x))
        return self.fc3(x)

# Generate data
X = np.linspace(0, 2*np.pi, 100).reshape(-1, 1).astype(np.float32)
y = np.sin(X).astype(np.float32)

def train_model():
    # Initialize model with explicit FP32
    model = TinyModel().float()
    
    # Modern quantization config to avoid warnings
    model.qconfig = torch.quantization.QConfig(
        activation=torch.quantization.HistogramObserver.with_args(
            quant_min=0,
            quant_max=255,
            dtype=torch.quint8
        ),
        weight=torch.quantization.PerChannelMinMaxObserver.with_args(
            quant_min=-128,
            quant_max=127,
            dtype=torch.qint8
        )
    )
    
    torch.quantization.prepare_qat(model, inplace=True)

    criterion = nn.MSELoss()
    optimizer = torch.optim.AdamW(model.parameters(), lr=0.01, weight_decay=1e-4)

    inputs = torch.from_numpy(X).float()
    targets = torch.from_numpy(y).float()

    for epoch in range(500):
        optimizer.zero_grad()
        outputs = model(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()

    # Plot results
    with torch.no_grad():
        predictions = model(inputs)
    
    plt.figure(figsize=(10, 5))
    plt.plot(X, y, label='True Sine Wave')
    plt.plot(X, predictions.numpy(), label='Predictions', linestyle='--')
    plt.title('Sine Wave Prediction')
    plt.xlabel('X')
    plt.ylabel('sin(X)')
    plt.legend()
    plt.show()

    # Final quantization conversion
    model = torch.quantization.convert(model, inplace=True)
    torch.save(model.state_dict(), "tiny_sine_model.pth")

if __name__ == "__main__":
    plt.plot(X, y, label='Sine Wave')
    plt.title('Original Sine Wave')
    plt.xlabel('X')
    plt.ylabel('sin(X)')
    plt.legend()
    plt.show()
    
    train_model()