package pex.core.expression.compositeexpression.unaryexpression;

import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Neg extends UnaryExpression{

	public Neg(Expression e){
		setArguments(e);
	}

	public String getName(){
		return "neg";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			return new IntegerLiteral(-((IntegerLiteral)getArguments().evaluate()).intValue());
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}