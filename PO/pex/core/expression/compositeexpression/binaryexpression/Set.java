package pex.core.expression.compositeexpression.binaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.Interpreter;
import pex.app.App;
import pex.core.Program;
import pex.app.BadExpressionException;

public class Set extends BinaryExpression{

	private Program _prog;

	public Set(Expression e1, Expression e2, Program prog){
		setArguments(e1, e2);
		_prog = prog;
	}

	public String getName(){
		return "set";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			Literal literal = (Literal)getSecondArgument().evaluate(); 
			_prog.setIdentifierValue(getFirstArgument().getAsText(), literal);
			return literal;
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}	
	}
}
