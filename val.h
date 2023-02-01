#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;

enum ValType { VINT, VREAL, VSTRING, VBOOL, VERR };

class Value {
    ValType	T;
    bool    Btemp;
	int		Itemp;
	float   Rtemp;
    string	Stemp;
       
public:
    Value() : T(VERR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0), Stemp("") {}
    Value(int vi) : T(VINT), Btemp(false), Itemp(vi), Rtemp(0.0), Stemp("") {}
	Value(float vr) : T(VREAL), Btemp(false), Itemp(0), Rtemp(vr), Stemp("") {}
    Value(string vs) : T(VSTRING), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(vs) {}
    
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
    bool IsInt() const { return T == VINT; }
    bool IsString() const { return T == VSTRING; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}
    
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    string GetString() const { if( IsString() ) return Stemp; throw "RUNTIME ERROR: Value not a string"; }
    
    float GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a boolean";}
    
    void SetType(ValType type)
    {
    	T = type;
	}
	
    void SetInt(int val)
    {
    	Itemp = val;
	}
	
	void SetReal(float val)
    {
    	Rtemp = val;
	}
	
	void SetString(string val)
    {
    	Stemp = val;
	}
	
	void SetBool(bool val)
    {
    	Btemp = val;
	}
	
	
    // add op to this
    Value operator+(const Value& op) const {
        if(op.IsString() && T == VSTRING) {
            string newstring = Stemp + op.GetString();
            return Value(newstring);
        }
        else if (op.IsInt()) {
            if (T == VINT) {
                return Value(op.GetInt() + Itemp);
            }
            else if (T == VREAL) {
                return Value((float)op.GetInt() + Rtemp);
            }
        }
        else if (op.IsReal()) {
            if (T == VINT) {
                return Value(op.GetReal() + (float)Itemp);
            }
            else if (T == VREAL) {
                return Value(op.GetReal() + Rtemp);
            }
        }
        return Value();
        
    }
    
    // subtract op from this
    Value operator-(const Value& op) const {
        if (op.IsInt()) {
            if (T == VINT) {
                return Value(Itemp - op.GetInt());
            }
            else if (T == VREAL) {
                return Value(Rtemp - (float)op.GetInt());
            }
        }
        else if (op.IsReal()) {
            if (T == VINT) {
                return Value((float)Itemp - op.GetReal());
            }
            else if (T == VREAL) {
                return Value(Rtemp - op.GetReal());
            }
        }
        return Value();
    }
    
    // multiply this by op
    Value operator*(const Value& op) const {
        if (op.IsInt()) {
            if (T == VINT) {
                return Value(Itemp * op.GetInt());
            }
            else if (T == VREAL) {
                return Value(Rtemp * (float)op.GetInt());
            }
        }
        else if (op.IsReal()) {
            if (T == VINT) {
                return Value(Itemp * op.GetReal());
            }
            else if (T == VREAL) {
                return Value(Rtemp * op.GetReal());
            }
        }
        return Value();
    }
    
    // divide this by op
    Value operator/(const Value& op) const {
        if (op.IsInt()) {
            if (T == VINT) {
                return Value(Itemp / op.GetInt());
            }
            else if (T == VREAL) {
                return Value(Rtemp / op.GetInt());
            }
        }
        else if (op.IsReal()) {
            if (T == VINT) {
                return Value(Itemp / op.GetReal());
            }
            else if (T == VREAL) {
                return Value(Rtemp / op.GetReal());
            }
        }
        return Value();
    }
    
    Value operator==(const Value& op) const {
        if (T == VERR) {
            return Value();
        }
        else if (op.GetType() == VERR) {
            return Value();
        }
        else if (T == op.GetType()) {
            //if (this == op)
            if (T == VSTRING) {
                if (Stemp == op.GetString()) {
                    return Value(true);
                }
            }
            else if (T == VINT) {
                if (Itemp == op.GetInt()) {
                    return Value(true);
                }
            }
            else if (T == VREAL) {
                if (Rtemp == op.GetReal()) {
                    return Value(true);
                }
            }
            else if (T == VBOOL) {
                if (Btemp == op.GetBool()) {
                    return Value(true);
                }
            }
            return Value(false);
        }
        else if (T == VREAL && op.IsInt()) {
            if (Rtemp == op.GetInt()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        else if (T == VINT && op.IsReal()) {
            if (Itemp == op.GetReal()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        return Value();
    }
    

	Value operator>(const Value& op) const {
        if (T == op.GetType()) {
            if (T == VSTRING) {
                if (Stemp > op.GetString()) {
                    return Value(true);
                }
            }
            else if (T == VINT) {
                if (Itemp > op.GetInt()) {
                    return Value(true);
                }
            }
            else if (T == VREAL) {
                if (Rtemp > op.GetReal()) {
                    return Value(true);
                }
            }
            return Value(false);
        }
        else if (T == VREAL && op.IsInt()) {
            if (Rtemp > op.GetInt()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        else if (T == VINT && op.IsReal()) {
            if (Itemp > op.GetReal()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        return Value();
    }
	
	Value operator<(const Value& op) const {
        if (T == op.GetType()) {
            if (T == VSTRING) {
                if (Stemp < op.GetString()) {
                    return Value(true);
                }
            }
            else if (T == VINT) {
                if (Itemp < op.GetInt()) {
                    return Value(true);
                }
            }
            else if (T == VREAL) {
                if (Rtemp < op.GetReal()) {
                    return Value(true);
                }
            }
            return Value(false);
        }
        else if (T == VREAL && op.IsInt()) {
            if (Rtemp < op.GetInt()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        else if (T == VINT && op.IsReal()) {
            if (Itemp < op.GetReal()) {
                return Value(true);
            }
            else {
                return Value(false);
            }
        }
        return Value();
    }
	
	    
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.Itemp;
        else if( op.IsString() ) out << op.Stemp;
        else if( op.IsReal()) out <<  fixed << showpoint << setprecision(2) << op.Rtemp;
        else out << "ERROR";
        return out;
    }
};


#endif
