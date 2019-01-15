package com.adjust.test;

public class Adjust2dxCommandJsonListenerCallback implements ICommandJsonListener {
	public native void executeCommand2dx(String className, String methodName, String jsonParameters);
	
	public Adjust2dxCommandJsonListenerCallback() {}
	
	@Override
	public void executeCommand(String className, String methodName, String jsonParameters) {
		executeCommand2dx(className, methodName, jsonParameters);
	}
}
