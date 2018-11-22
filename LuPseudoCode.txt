class DynamicObj:
	array [N] vertex;
	array [M] constraints
	
class vertex(i):
	mass mi;		//mass of the point
	pos xi;			//point position
	vel vi:			//point velocity

class constraints(j):
	cardinality nj;		//How many vertices are involved
	func Cj(R^3nj -> R);   	//
	indices {i1, ... inj}; 	// 
	float stiffness;	//
	bool equality();	// defined by Cj 


(1) forall vertices i
(2) 	initialize xi = x0i ,vi = v0i, wi = 1/mi		    	//Initialize state variables
(3) endfor							    
(4) loop
(5) 	forall vertices i do vi ← vi +∆twifext(xi)		    
(6) 		dampVelocities(v1,...,vN)			    
(7) 	forall vertices i do pi ← xi +∆tvi			   	//estimates pi for new locations are calculated using expl Eul Int Step
(8) 	forall vertices i do generateCollisionConstraints(xi → pi)
(9) 	loop solverIterations times				 	//Iterative solver that manipulates pos 
(10) 		projectConstraints(C1,...,CM+Mcoll ,p1,...,pN)		//estimates to satisfy the constraints (repeatidly projetcs each
(11) 	endloop								//constraint in a Gauss-Seidel type fashion) (section 3.2)
(12) 	forall vertices i
(13) 		vi ← (pi −xi)/∆t					//Pos of vertices moved to the optimized estimaets and the velocities are updated accordingly
(14) 		xi ← pi
(15) 	endfor
(16) 	velocityUpdate(v1,...,vN)
(17) endloop
