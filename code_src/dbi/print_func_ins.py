import pyqbdi
import ctypes

target_so = "/home/xiao-sa/software/test_qbdi/mylib.so"

mylib = ctypes.cdll.LoadLibrary(target_so)
funcPtr = ctypes.cast(mylib._Z5hellov, ctypes.c_void_p).value

vm = pyqbdi.VM()

state = vm.getGPRState()
fakestack = pyqbdi.allocateVirtualStack(state, 0x100000)
assert fakestack != None

def showInstruction(vm, gpr, fpr, data):
    # Obtain an analysis of the instruction from the VM
    instAnalysis = vm.getInstAnalysis()

    # Printing disassembly
    print("0x{:x}: {}".format(instAnalysis.address, instAnalysis.disassembly))

    return pyqbdi.CONTINUE

cid = vm.addCodeCB(pyqbdi.PREINST, showInstruction, None)

assert vm.addInstrumentedModuleFromAddr(funcPtr)

asrun, retval = vm.call(funcPtr, [])
