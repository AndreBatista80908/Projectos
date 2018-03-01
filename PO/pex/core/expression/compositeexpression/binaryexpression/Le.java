package pex.core.expression.compositeexpression.binaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Le extends BinaryExpression{

	public Le(Expression e1, Expression e2){
		setArguments(e1, e2);
	}

	public String getName(){
		return "le";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			return new IntegerLiteral(((IntegerLiteral)getFirstArgument().evaluate()).intValue() <= ((IntegerLiteral)getSecondArgument().evaluate()).intValue() ? 1 : 0);
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}
