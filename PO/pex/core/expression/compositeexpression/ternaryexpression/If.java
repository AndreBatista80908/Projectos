package pex.core.expression.compositeexpression.ternaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class If extends TernaryExpression{

	public If(Expression e1, Expression e2, Expression e3){
		setArguments(e1, e2, e3);
	}

	public String getName(){
		return "if";
	}

	public Literal evaluate() throws BadExpressionException {
		Literal literal = new IntegerLiteral(0);
		try{
			literal = ((((IntegerLiteral)getFirstArgument().evaluate()).intValue() != 0) ? getSecondArgument().evaluate() : getThirdArgument().evaluate());
			return literal;
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}
