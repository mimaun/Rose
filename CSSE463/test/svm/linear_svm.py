import numpy as np
import matplotlib.pyplot as plt
from matplotlib import style
style.use('ggplot')
from sklearn import svm

# coordinates
x = [1.3, 5, 1.5, 8, 1, 7, 3, 6]
y = [1, 8, 1.9, 7, 0.6, 10, 2.4, 8.6]

# visualize
# plt.scatter(x, y)
# plt.show()

# X is a collection of features
X = np.array([
    [1.3, 1],
    [5, 8],
    [1.5, 1.9],
    [8, 7],
    [1, 0.6],
    [7, 10],
    [3, 2.4],
    [6, 8.6]
    ])
# Y is label
Y = [0, 1, 0, 1, 0, 1, 0, 1]

# define classifier
clf = svm.SVC(kernel = 'linear', C = 1.0)

# learn
clf.fit(X, Y)

# predict
testData = [2.5, 4]
print clf.predict(testData)

# visualize
# coef: Weights assigned to the features (coefficients in the primal problem)
weight = clf.coef_[0]
print weight

a = -weight[0] / weight[1]

xx = np.linspace(0, 11)
yy = a * xx - clf.intercept_[0] / weight[1]

h0 = plt.plot(xx, yy, 'k-', label = 'non weighted div')

plt.scatter(X[:, 0], X[:, 1], c = Y)
plt.legend()
plt.show()

