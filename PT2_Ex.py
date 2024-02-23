import math,copy
import numpy as np
import matplotlib.pyplot as plt
import torch
#Pytorch foundamentals 2 exercises

#create 'known' parameters
weight = 0.3
bias = 0.9

#create data
start = 0
end = 10
step = 0.1
X = torch.arange(start, end, step).unsqueeze(dim=1)
Y = weight*X + bias

#split data
train_split = int(0.8*len(X))
X_train, Y_train = X[:train_split], Y[:train_split]
X_test, Y_test = X[train_split:], Y[train_split:]

#visualize the data
def plot_data(train_data = X_train, train_labels = Y_train, test_data = X_test, test_labels = Y_test, predictions = None):
    plt.figure(figsize=(10,7))
    plt.scatter(train_data, train_labels, c='b', s=4, label='Training data')
    plt.scatter(test_data, test_labels, c='g', s=4, label='Testing data')
    if predictions is not None:
        plt.scatter(test_data, predictions, c='r', s=4, label='Predictions')
    plt.legend(prop={'size':14})
    plt.show()
    
#plot_data()

#build a model
class LinearRegressionModel(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.linear_layer1 = torch.nn.Linear(in_features=1, out_features=1)
    
    def forward(self, x):
        return self.linear_layer1(x)
    
#instantiate the model
model = LinearRegressionModel()
trainLoss = []
testLoss = []
epochsToPlot = []

#create loss and optimizer
loss_function = torch.nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

#training the model
epochs = 1000

for epoch in range(epochs):
    #forward pass
    predictions = model(X_train)
    loss = loss_function(predictions, Y_train)
    
    #backward pass
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()
    
    #track the loss
    trainLoss.append(loss.item())
    testLoss.append(loss_function(model(X_test), Y_test).item())
    epochsToPlot.append(epoch)
    
#plot the loss
plt.figure(figsize=(10,7))
plt.plot(epochsToPlot, trainLoss, label='Train loss')   
plt.plot(epochsToPlot, testLoss, label='Test loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
#plt.show()

#make predictions
predictions = model(X_test)
#plot_data( predictions=predictions.detach())#detach() is used to remove the gradient from the tensor

    
#Save the model
torch.save(model.state_dict(), 'linear_regression_model.pt')

#Load the model
loaded_model = LinearRegressionModel()
loaded_model.load_state_dict(torch.load('linear_regression_model.pt'))
loaded_model.eval()
print(loaded_model(X_test)==model(X_test))#predictions from the loaded model
#print(model(X_test))#predictions from the original model

        
    
        
        
