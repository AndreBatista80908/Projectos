package pex.core.expression.literal;

import java.util.*;
import pex.core.Expression;

public class StringLiteral extends Literal{

	private String _value = "";

	public StringLiteral(String value){
		_value = value;
	}

	public String getAsText(){
		return "\""+stringValue()+"\"";
	}

	public String getName(){
		return "";
	}

	public String stringValue(){
		return _value;
	}

	@Override
	public Literal evaluate() {
		return new StringLiteral(stringValue());
	}
}
