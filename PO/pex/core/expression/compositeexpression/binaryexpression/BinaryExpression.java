package pex.core.expression.compositeexpression.binaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;

public abstract class BinaryExpression extends CompositeExpression{
	
	private Expression _e1;
	private Expression _e2;

	public void setArguments(Expression e1, Expression e2){
		_e1 = e1;
		_e2 = e2;
	}

	public Expression getFirstArgument(){ 
		return _e1; 
	}

	public Expression getSecondArgument(){ 
		return _e2; 
	}

	public String getAsText(){
		return "(" + getName() + " " + _e1.getAsText() + " " + _e2.getAsText() + ")";
	}
}
