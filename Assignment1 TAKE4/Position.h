#ifndef POSITION_H
#define POSITION_H


struct position {
	int row,
		col;
	
	operator int() const { return row; }
	
};

#endif