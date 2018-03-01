package pex.core.expression.compositeexpression.binaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.app.BadExpressionException;

public class While extends BinaryExpression{

	public While(Expression e1, Expression e2){
		setArguments(e1, e2);
	}

	public String getName(){
		return "while";
	}

	public Literal evaluate() throws BadExpressionException {	
		try{
			while(((IntegerLiteral)getFirstArgument().evaluate()).intValue() != 0){
				getSecondArgument().evaluate();
			}
			return new IntegerLiteral(0);
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}	
	}
}