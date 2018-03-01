package pex.core.expression.compositeexpression;

import java.util.*;
import pex.AppIO;
import pex.core.Expression;
import pex.core.expression.literal.Literal;
import pex.core.expression.literal.IntegerLiteral;
import pex.core.expression.compositeexpression.CompositeExpression;
import pex.app.BadExpressionException;

public class ReadI extends CompositeExpression {

	private AppIO _io;

	public ReadI(AppIO io){
		_io = io;
	}

	public String getAsText(){
		return "(" + getName() + ")";
	}

	public String getName(){
		return "readi";
	}

	public Literal evaluate() throws BadExpressionException {
		try{
        	return new IntegerLiteral(_io.readInteger());
        } catch (ClassCastException cast){
			throw new BadExpressionException(this.getAsText());
		} 
	}
}
