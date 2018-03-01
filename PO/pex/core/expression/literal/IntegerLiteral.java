package pex.core.expression.literal;

import java.util.*;
import pex.core.Expression;

public class IntegerLiteral extends Literal{

	private int _value = 0;
	
	public IntegerLiteral(int value){
		_value = value;
	}

	public String getAsText(){
		return "" + intValue();
	}

	public String getName(){
		return "";
	}

	public int intValue(){
		return _value;
	}

	@Override
	public Literal evaluate() {
		// TODO Auto-generated method stub
		return this;
	}
	
	public String stringValue(){
		return ""+_value;
	}
}
