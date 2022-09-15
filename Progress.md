# Notes for Directed Study of Elliptic Curves
## Review of Elliptic Curves (Sep. 12 - Sep. 18)
### Definition
An elliptic curve is a plane curve defined by the equation y<sup>2</sup> = f(x) = x<sup>3</sup> + ax + b (a,b ∈ K), where f(x) is a cubic polynomial with no repeated roots (4a<sup>3</sup> + 27b<sup>2</sup> ≠ 0).
### Singularity
Take the definition as F(x,y) = 0, then a point (x,y) is non-singular (or a smooth point) if ∂F/∂x or ∂F/∂y ≠ 0.  
In this way, with the cubic (x<sup>3</sup>), no multiple roots == all points are non-singular.
### Field of characteristic 2
The simplest field with characteristic 2 is F<sub>2</sub> = Z/2Z -> 1 + 1 (2 times) = 0 (mod 2).  
More generally, for every n ≥ 1, there is exactly one field of cardinality 2<sup>n</sup> up to isomorphism, denoted F<sub>2</sub>n. Like all fields of characteristic 2, these fields contain F<sub>2</sub> as a subfield.  
Given any field K of characteristic 2, the algebraic closure of K also has characteristic 2. For example, the algebraic closure of F<sub>2</sub> can be considered the union of all the fields F<sub>2</sub>n.  
### Elliptic curves with char(K) = 2 or 3 are INSECURE
#### Not secure
As 4a<sup>3</sup> + 27b<sup>2</sup> = 2<sup>2</sup>a<sup>3</sup> + 3<sup>3</sup>b<sup>2</sup>, so with char(K) = 2 or 3, 4a<sup>3</sup> + 27b<sup>2</sup> = 0 always holds, and so the previous definition of elliptic curves is violated.  
There is no known subexponential-cost algorithm for computing discrete logs in elliptic curves over fields of small characteristic.
#### Further generalization
If we use a more general definition: **y<sup>2</sup> + a<sub>1</sub>xy + a<sub>3</sub>y = x<sup>3</sup> + a<sub>2</sub>x<sup>2</sup> + a<sub>4</sub>x + a<sub>6</sub>**, then char(K) = 2 or 3 is no longer a problem.  
More explicitly, char(K) = 2 gets y<sup>2</sup> + y = x<sup>3</sup> + ax + b (together with O); char(K) = 3 gets y<sup>2</sup> = x<sup>3</sup> + ax<sup>2</sup> + bx + c (together with O).
