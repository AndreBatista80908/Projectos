package pex.core.expression.compositeexpression.unaryexpression;

import pex.core.Expression;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;

public abstract class UnaryExpression extends CompositeExpression{
	
	private Expression _e1;

	public Expression getArguments(){ 
		return _e1; 
	}

	public void setArguments(Expression e1){ 
		_e1 = e1;
	}

	public String getAsText(){
		return "(" + getName() + " " + _e1.getAsText() + ")";
	}
}
