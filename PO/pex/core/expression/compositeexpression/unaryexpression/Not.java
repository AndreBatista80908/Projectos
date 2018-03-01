package pex.core.expression.compositeexpression.unaryexpression;

import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Not extends UnaryExpression{

	public Not(Expression e){
		setArguments(e);
	}

	public String getName(){
		return "not";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			return new IntegerLiteral((((IntegerLiteral)getArguments().evaluate()).intValue() != 0) ? 0 : 1);
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}