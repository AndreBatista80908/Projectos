package pex.core;

import java.util.*;
import pex.core.expression.literal.Literal;
import pex.app.BadExpressionException;
import java.io.Serializable;

public abstract class Expression implements Serializable{
	public abstract String getAsText();
	public abstract Literal evaluate() throws BadExpressionException;
	public abstract String getName();
}
