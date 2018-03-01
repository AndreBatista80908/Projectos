package pex.core.expression;

import java.util.*;
import pex.core.Expression;
import pex.core.Interpreter;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;

public class Identifier extends Expression{

	private String _name;
	private Interpreter _interp;

	public Identifier(String name, Interpreter interp){
		_name = name;
		_interp = interp;
	}

	@Override
	public String getAsText(){
		return getName();
	}

	@Override
	public String getName(){
		return _name;
	}

	@Override
	public Literal evaluate(){
		Literal lit = _interp.getIdentifierValue(_name);
		if (lit == null) 
			return new IntegerLiteral(0);
		return lit;
	}
}
