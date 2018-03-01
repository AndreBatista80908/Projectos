package pex.core.expression.compositeexpression.binaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class Or extends BinaryExpression{

	public Or(Expression e1, Expression e2){
		setArguments(e1, e2);
	}

	public String getName(){
		return "or";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
		if(((IntegerLiteral)getFirstArgument().evaluate()).intValue() == 0)
			return new IntegerLiteral((((IntegerLiteral)getSecondArgument().evaluate()).intValue() != 0) ? 1 : 0);
		else
			return new IntegerLiteral(1);
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}	
	}
}
