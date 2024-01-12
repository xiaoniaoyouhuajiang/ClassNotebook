## 学习Thinc

### 概念与原理
参照thinc.ai/docs/concept，首先，关于反向传播以及计算图的学习可以看资料：openmlsys.github.io，里面对于反向传播误差的描述最为清晰

#### 可组合性
使用普通的方法，在进行反向传播的过程中，`权重差`不能传播到中间层

在不使用反向自动微分机制（大多数dl框架的设计策略）的情况下，我们可以使用higher order function，我们所见到的问题其实非常简单：我们希望获得推理结果的同时，也能够获得剃度；解决这个问题的办法就是`callback`，大致思路如下：

```python
def forward(X: InT) -> Tuple[OutT, Callable[[OutT], Int]]:
    Y: OutT = _do_compute(X)

    def backward(dY: OutT) -> InT:
        dX: InputType = _do_backprop(dY, X)
        return dX

    return Y, backward

def chain(layer1, layer2):
    def forward_chain(X):
        Y, get_dX = layer1(X)
        Z, get_dY = layer2(Y)

        def backprop_chain(dZ):
            dY = get_dY(dZ)
            dX = get_dX(dY)
            return dX
        
        return Z, backprop_chain

    return forward_chain
```
