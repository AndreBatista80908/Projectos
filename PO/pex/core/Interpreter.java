package pex.core;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import pex.parser.BadNumberException;
import pex.parser.BadSourceException;
import pex.parser.EndOfInputException;
import pex.parser.InvalidExpressionException;
import pex.parser.MissingClosingParenthesisException;
import pex.parser.UnknownOperationException;
import pex.parser.NewParser;
import java.util.*;
import java.io.Serializable;
import pex.AppIO;
import pex.core.Program;
import pex.core.expression.Identifier;
import pex.core.expression.literal.Literal;

public class Interpreter implements Serializable{

	private String _name;
	private Map<String, Program> _progs;
	private Map<String, Literal> _ids;
	private AppIO _io1;

	public Interpreter(AppIO io1){
		_progs = new HashMap<>();
		_ids = new TreeMap<>();
		_io1 = io1;
	}

	public void setIdentifierValue(String name, Literal value){
		_ids.put(name, value);
	}
	
	public Literal getIdentifierValue(String name){
		return _ids.get(name);
	}

	public void addProgram(Program p){
		_progs.put(p.getName(), p);
	}

	public Program getProgram(String name){
		return _progs.get(name);
	}

	public boolean containProgram(String name) {
		return _progs.containsKey(name);
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		this._name = name;
	}

	public void save(String name) {
		try{
			ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(name));
			out.writeObject(this);
			out.close();
		}
		catch(IOException e){
		}
	}

	public void readProgram(String name, Interpreter i) {
		NewParser prs = new NewParser();
		try {
			Program _prog = prs.parseFile(name, name,i);
			addProgram(_prog);
		} catch (BadSourceException e) {
			e.printStackTrace();
		} catch (BadNumberException e) {
			e.printStackTrace();
		} catch (InvalidExpressionException e) {
			e.printStackTrace();
		} catch (MissingClosingParenthesisException e) {
			e.printStackTrace();
		} catch (UnknownOperationException e) {
			e.printStackTrace();
		} catch (EndOfInputException e) {
			e.printStackTrace();
		}
	}
	
	public void writeProgram(String progrName, String file) {
		Program _prog = getProgram(progrName);
		_prog.writeToTextFile(file);
	}

	public void createProgram(String name, Interpreter interp) {
		Program p = new Program(name, interp);
		addProgram(p);
	}

	public AppIO getAppIO(){
		return _io1;
	}
}
