package pex.core.expression.compositeexpression.ternaryexpression;

import pex.core.Expression;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;

public abstract class TernaryExpression extends CompositeExpression{
	
	private Expression _e1;
	private Expression _e2;
	private Expression _e3;

	public void setArguments(Expression e1, Expression e2, Expression e3){
		_e1 = e1;
		_e2 = e2;
		_e3 = e3;
	}

	public Expression getFirstArgument(){ 
		return _e1; 
	}

	public Expression getSecondArgument(){ 
		return _e2; 
	}

	public Expression getThirdArgument(){ 
		return _e3; 
	}

	public String getAsText(){
		return "(" + getName() + " " + _e1.getAsText() + " " + _e2.getAsText() + " " + _e3.getAsText() + ")";
	}
}
