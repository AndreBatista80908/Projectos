package pex.core.expression.compositeexpression.unaryexpression;

import java.util.*;
import pex.core.Expression;
import pex.core.Program;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.StringLiteral;
import pex.app.BadExpressionException;

public class Call extends UnaryExpression{

	private Program _prog;

	public Call(StringLiteral e, Program prog){
		setArguments(e);
		_prog = prog;
	}

	public String getName(){
		return "call";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
			Program p = _prog.getProgram(((StringLiteral)getArguments()).stringValue());
			Literal literal = p.execute(); 
			return literal;
		} catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		}
	}
}
