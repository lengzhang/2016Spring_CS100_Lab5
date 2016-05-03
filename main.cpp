#include <iostream>
#include <string.h>

#include <vector>
#include <list>
#include <math.h>

using namespace std;

//—————Base—————

class Base
{
	public:
		/* Constructors */
		Base () {};
		/* Pure Virtual Functions */
		virtual double evaluate () = 0;
		virtual void print () = 0;
};

//—————Op—————

class Op: public Base
{
	public:
		Op (const double new_num)
		{
			num = new_num;
		};

		void setNum (const double new_num)
		{
			num = new_num;
		};
		
		double getNum ()
		{
			return num;
		};
		
		virtual double evaluate ()
		{
			return num;
			
		};
		
		virtual void print ()
		{
			cout << num;
		};
		
	private:
		double num;
};

//—————Mult—————

class Mult: public Base
{
	public:
		Mult (Base* new_op1, Base* new_op2)
        	{
            		op1 = new_op1;
            		op2 = new_op2;
        	};
	
	        Mult (Base* new_op1, const double x)
        	{
            		op1 = new_op1;
            		op2 = new Op(x);
        	};
	
        	Mult (const double y, const double x)
        	{
        	    op1 = new Op(y);
        	    op2 = new Op(x);
        	};
	
      		Mult (const double y, Base* new_op2)
        	{
            		op1 = new Op(y);
            		op2 = new_op2;
        	};
	
      		virtual double evaluate()
        	{
            		return op1->evaluate() * op2->evaluate();
        	};
        
        	virtual void print ()
        	{
            		op1->print();
            		cout << " * ";
            		op2->print();
        	};
        
	private:
        	Base* op1;
        	Base* op2;
};

//—————Sub—————

class Sub: public Base
{
	public:
        	Sub (Base* new_op1, Base* new_op2)
        	{
        		op1 = new_op1;
            		op2 = new_op2;
        	};
	
        	Sub (Base* new_op1, const double x)
        	{
            		op1 = new_op1;
            		op2 = new Op(x);
        	};
	
        	Sub (const double y, const double x)
        	{
            		op1 = new Op(y);
            		op2 = new Op(x);
        	};
	
        	Sub (const double y, Base* new_op2)
        	{
            		op1 = new Op(y);
            		op2 = new_op2;
   		};
	
        	virtual double evaluate()
        	{
            		return op1->evaluate() - op2->evaluate();
        	};
        
        	virtual void print ()
        	{
            		op1->print();
            		cout << " - ";
           		op2->print();
        	};
        
	private:
       		Base* op1;
       		Base* op2;
};

//—————Div—————

class Div: public Base
{
	public:
        	Div (Base* new_op1, Base* new_op2)
        	{
            		op1 = new_op1;
            		op2 = new_op2;
       		};
	
        	Div (Base* new_op1, const double x)
        	{
            		op1 = new_op1;
            		op2 = new Op(x);
        	};
	
        	Div (const double y, const double x)
        	{
            		op1 = new Op(y);
            		op2 = new Op(x);
        	};
	
		Div (const double y, Base* new_op2)
       		{
            		op1 = new Op(y);
            		op2 = new_op2;
        	};
	
        	virtual double evaluate()
        	{
            		return op1->evaluate() / op2->evaluate();
        	};
        
        	virtual void print ()
        	{
            		op1->print();
            		cout << " / ";
            		op2->print();
        	};
        
	private:
        	Base* op1;
        	Base* op2;
};

//—————Add—————

class Add: public Base
{
	public:
		Add (Base* new_op1, Base* new_op2)
		{
			op1 = new_op1;
			op2 = new_op2;
		};
		
		Add (const double new_op1, const double new_op2)
		{
			op1 = new Op(new_op1);
			op2 = new Op(new_op2);
		};
		
		Add (Base* new_op1, const double new_op2)
		{
			op1 = new_op1;
			op2 = new Op(new_op2);
		};
		
		Add (const double new_op1, Base* new_op2)
		{
			op1 = new Op(new_op1);
			op2 = new_op2;
		};
		
		virtual double evaluate()
		{
			return op1->evaluate() + op2->evaluate();
		};
		
		virtual void print ()
		{
			op1->print();
			cout << " + ";
			op2->print();
		};

	private:
		Base* op1;
		Base* op2;
};

//—————Sqr—————

class Sqr: public Base
{
	public:
        	Sqr (Base* new_op1)
        	{
            		op1 = new_op1;
        	};
	
		Sqr (const double y)
        	{
           		op1 = new Op(y);
        	};
    
        	virtual double evaluate()
        	{
            		double i=op1->evaluate();
            		return i * i;
        	};
        
        	virtual void print ()
        	{
            		op1->print();
            		cout << "^ 2";
        	};
        
	private:
        	Base* op1;
};

//—————Container—————

class Sort;

class Container
{
	protected:
       		Sort * sort_function;
       	
   	public:
       		Container () : sort_function ( NULL ){};
       		Container ( Sort * function ) : sort_function ( function ) {};
    
		void set_sort_function ( Sort * sort_function );

       		virtual void add_element ( Base * element ) = 0 ;
       		virtual void print () = 0 ;
       		virtual void sort () = 0 ;
    
       		virtual void swap ( int i , int j ) = 0 ;
       		virtual Base * at ( int i ) = 0 ;
       		virtual int size () = 0 ;
       	
       		virtual void insert ( const int i, Base * new_Item ) = 0;
       		virtual void remove ( const int i ) = 0;
};

//—————Sort—————

class Sort
{
	public:
		Sort () {};

		virtual void sort ( Container * container ) = 0 ;
};

//—————SelectionSort—————

class SelectionSort: public Sort
{
	public:
		virtual void  sort ( Container * container )
		{
			int size = container -> size ();
			for ( int i = 0; i < size - 1; i++ )
			{
				int min_it = i;
				for ( int j = i + 1; j < size; j++ ){
					if ( container -> at ( min_it ) -> evaluate () > container -> at ( j ) -> evaluate () )
						min_it = j;
				}
				if ( min_it != i )
					container -> swap ( i, min_it );
			}
		};
};

//—————BubbleSort—————

class BubbleSort: public Sort
{
	public:
		virtual void sort ( Container * container )
		{
			int size = container -> size ();
			bool swapped;
			do
			{
				swapped = false;
				for ( int i = 0; i < size - 1; i++ )
				{
					if ( container -> at ( i ) -> evaluate () > container -> at ( i + 1 ) -> evaluate () )
					{
						container -> swap ( i, i + 1);
						swapped = true;
					}
				}
			} while ( swapped ); 
		};
};

//—————VectorContainer—————

class VectorContainer: public Container
{
	public:
		void set_sort_function ( Sort * sort_function )
		{
			this->sort_function = sort_function;
		};
		
		virtual void add_element ( Base * element )
		{
			vectorContainer.push_back ( element );
		};
		
        	virtual void print ()
        	{
			if ( this -> size () == 0)
				cout << "Container is empty." << endl;
			else
				for ( int i = 0; i < this -> size (); i++ )
					cout << this -> at ( i ) -> evaluate () << endl;
		};
		
        	virtual void sort ()
        	{
			sort_function -> sort ( this );
		};
    
        	virtual void swap ( int i , int j )
        	{
			Base * temp = vectorContainer[i];
			vectorContainer[i] = vectorContainer[j];
			vectorContainer[j] = vectorContainer[i];
		};
		
        	virtual Base * at ( int i )
        	{
        		return vectorContainer[i];
        	
        	};
        
        	virtual int size ()
        	{
        		return vectorContainer.size();
        	
        	};
        
        	virtual Base *& operator [] ( const int i )
        	{
        		return vectorContainer[i];
        	};

		virtual void insert ( const int i, Base * new_Item )
		{
			vectorContainer.insert( vectorContainer.begin() + i, new_Item );
		};
		
		virtual void remove ( const int i )
		{
			vectorContainer.erase( vectorContainer.begin() + i );
		};
		
	protected:
		Sort * sort_function;

	private:
		vector < Base * > vectorContainer;
};

//—————ListContainer—————

class ListContainer: public Container
{
	public:
		void set_sort_function ( Sort * sort_function )
		{
			this->sort_function = sort_function;
		};

		virtual void add_element ( Base * element )
		{
			listContainer.push_back ( element );
		};
		
        	virtual void print ()
        	{
			if ( this -> size () == 0)
				cout << "Container is empty." << endl;
			else
				for ( int i = 0; i < this -> size (); i++ )
					cout << this -> at ( i ) -> evaluate () << endl;
		};
        	
        	virtual void sort ()
        	{
			sort_function -> sort ( this );
		};
    
        	virtual void swap ( int i , int j )
        	{
			list < Base * > :: iterator it_i = listContainer.begin();
			list < Base * > :: iterator  it_j = listContainer.begin();
			int k = 0;
			while ( k < i || k < j )
			{
				if ( k < i ) { it_i++; }
				if ( k < j ) { it_j++; }
				k++;
			}
			listContainer.insert ( it_i, *it_j );
			listContainer.insert ( it_j, *it_i );
			listContainer.erase ( it_i );
			listContainer.erase ( it_j );
		};
		
        	virtual Base * at ( int i )
		{
			list < Base * > :: iterator it;
			it = listContainer.begin ();
			for ( int j = 0; j < i; j++) { ++it; }
			return * it;
		};
        
        	virtual int size ()
        	{
        		return listContainer.size();
        	};
        
        	virtual void insert ( const int i, Base * new_Item )
		{
			list < Base * > :: iterator it = listContainer.begin();
			for ( int j = 0; j < i; j++)
				it++;
			listContainer.insert ( it, new_Item );
		};
		
		virtual void remove ( const int i )
		{
			list < Base * > :: iterator it = listContainer.begin();
			for ( int j = 0; j < i; j++)
				it++;
			listContainer.erase ( it );
		};
        	
	protected:
		Sort * sort_function;

	private:
		list < Base * > listContainer;
};

//—————Decorator—————

double Decorator( const string line )
{
  	char * equation = new char [line.length()+1];
  	strcpy (equation, line.c_str());
  	
	ListContainer * container = new ListContainer();
	vector < char * > opt;
	
	//Divide string to numbers and operators into container and opt
	char * pch = strtok( equation , " " );
	do
	{
		if ( (*pch == '+' || *pch == '-' || *pch == '*' || *pch == '/') && (strlen(pch) == 1) )
			opt.push_back( pch );
		else
			container -> add_element( new Op ( atof ( pch ) ) );
	} while ( ( pch = strtok ( NULL , " " ) ) != NULL );
	
	//Calculate Mult and Div
	int i = 0;
	do
	{
		if ( *opt[i] == '*' || *opt[i] == '/')
		{
			switch ( *opt[i] )
			{
				case '*':
					container -> insert( i, new Mult( container -> at( i ) , container -> at( i + 1 ) ) );
					break;
				case '/':
					container -> insert( i, new Div( container -> at( i ) , container -> at( i + 1 ) ) );
					break;
				default:
					break;
			}
			opt.erase( opt.begin() + i );
			container -> remove( i + 1 );
			container -> remove( i + 1 );
			i--;
		}
		i++;
	} while ( i < opt.size() );
	
	//Calculate Add and Sub
	while ( !opt.empty() )
	{
		if ( *opt[0] == '+' || *opt[0] == '-')
		{
			switch ( *opt[0] )
			{
				case '+':
					container -> insert( 0, new Add( container -> at( 0 ) , container -> at( 1 ) ) );
					break;
				case '-':
					container -> insert( 0, new Sub( container -> at( 0 ) , container -> at( 1 ) ) );
					break;
				default:
					break;
			}
			opt.erase( opt.begin() );
			container -> remove( 1 );
			container -> remove( 1 );
		}
	}
	return container -> at( 0 ) -> evaluate();
}

//—————Ceil—————

double Ceil ( const string equation )
{
	return ceil( Decorator( equation ) );
}

//—————Floor—————

double Floor ( const string equation )
{
	return floor( Decorator( equation ) );
}

//—————Abs—————

double Abs ( const string equation )
{
	return fabs( Decorator( equation ) );
}

//—————Main—————

int main ()
{
	char line []  = "-3.12 - 7 * 4 - 2 + 2.2 / 2";

	cout << "Equation: " << line << endl;

	cout << "Solution: " << Decorator( line ) << endl;
	
	cout << "Ceil:     " << Ceil( line ) << endl;
	
	cout << "Floor:    " << Floor( line ) << endl;
	
	cout << "Abs:      " << Abs( line ) << endl;

	return 0;
}