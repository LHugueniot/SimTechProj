class DynamicObj:
	array [N] vertex;
	array [M] constraints
	
class vertex(i):
	mass mi;				//mass of the point
	pos xi;					//point position
	vel vi:					//point velocity

class constraints(j):
	cardinality nj;			//How many particles does the constrain apply to
	func Cj(R^3nj -> R);   	//constraint function (similar to elastic potential, can be non negative)
	indices {i1, ... inj}; 	//set of particles affected by the constraint
	float stiffness;		//how stiff the constraint is
	bool equality();		// defined by Cj 


(1) forall vertices i												//
(2) 	initialize xi = x0i ,vi = v0i, wi = 1/mi		    		//Initialize state variables
(3) endfor							    							//wi is inverse mass
(4) loop
(5) 	forall vertices i do vi ← vi +∆t*wi*f_ext(xi)		    //∆t is timestamp, f_ext are external forces this is updating all the velocities based on the timestamp, external forces and the inverse weight
(6) 		dampVelocities(v1,...,vN)			    				//Dampening velocities, ex: v_new = 0.99 * v_old
(7) 	forall vertices i do pi ← xi +∆tvi			   				//estimates pi for new locations are calculated using expl Eul Int Step
(8) 	forall vertices i do generateCollisionConstraints(xi → pi)	//detects collisions and creates extra collisions (created on the fly)
(9) 	loop solverIterations times				 					//Iterative solver that manipulates pos 
(10) 		projectConstraints(C1,...,CM+Mcoll ,p1,...,pN)			//estimates to satisfy the constraints        {Main bulk of pbd}
(11) 	endloop														//constraint in a Gauss-Seidel type fashion) (section 3.2)
(12) 	forall vertices i
(13) 		vi ← (pi −xi)/∆t										//Pos of vertices moved to the optimized estimaets and the velocities are updated accordingly
(14) 		xi ← pi
(15) 	endfor
(16) 	velocityUpdate(v1,...,vN)
(17) endloop