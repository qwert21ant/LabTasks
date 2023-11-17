package ru.qwert21.labs.C2;

public class Core {
	private final Function[] functions = new Function[2];

	private int curMemoryInd = 0;
	private final double[] memory = new double[3];

	private double result = 0;

	public Core(Function function1, Function function2) {
		functions[0] = function1;
		functions[1] = function2;
	}

	public void eval(int functionInd, double x, double y, double z) {
		result = functions[functionInd].eval(x, y, z);
	}

	public double getResult() {
		return result;
	}

	public void clearResult() {
		result = 0;
	}

	public void setCurMemoryInd(int memoryInd) {
		curMemoryInd = memoryInd;
	}

	public double getMemory(int memoryInd) {
		return memory[memoryInd];
	}

	public void clearMemory() {
		memory[curMemoryInd] = 0;
	}

	public void addToMemory() {
		memory[curMemoryInd] += result;
		result = memory[curMemoryInd];
	}
}
