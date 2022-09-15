# Senior Thesis of Elliptic Curves
## Math Review
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

### Characteristic
#### Calculation
* O (infinity -- infinitely far up the y-axis) is taken as "zero element" (identity), -O = O, O + P = P
* -(x,y) = (x,-y)
* P + Q = -R (when P = Q, R is the only other point of intersection of *l* with the curve, and R could be O if *l* has double-tangency)
<div>
    <img src="./EC-Calculation.png" alt="Different Cases"/>
</div>

#### Over Real
##### Abelian
The set of points on an elliptic curve forms an abelian group (P + Q = Q + P).
##### Projective plane
For triples (X,Y,Z) (not all components 0),
* projective point: (λX,λY,λZ) ~ (X,Y,Z) for scalar λ, which forms an equivalence class
* when Z ≠ 0, we can find one and only one (x,y,1) from the equivalence class -> x = X/Z, y = Y/Z
* projective plane: all points (x,y) and *line at infinity* (points with Z = 0)

When more than one components on the triple (X,Y,Z) are 0, then we find the point O.
#### Over Complex
##### Lattice: L = Zω<sub>1</sub> + Zω<sub>2</sub>
##### Weierstrass ℘-function ℘<sub>L</sub>(z) -- P155
#### Over Rational -- P156
##### Hasse's Theorem -- P158
#### Extensions of finite fields and the Weil conjectures -- P158

## Cryptosystems
### Multiple of points
kP ∈ E can be found in O(logk log<sup>3</sup>q) bit operations by repeated doubling
* this is not always the best, like when p = 2 (char(K) = 2)
* if we know NP = 0 and k > N, then use k ≡ k mod N, and the time estimate becomes O(log<sup>4</sup>q) as N < q + 1 + 2√q = O(q)
### Imbedding plaintexts
* Encoding is not the same as Encryption.
* There is no polynomial time deterministic algorithm known for writing down a large number of points on an arbitrary E.
* There are probabilistic algorithms for which the chance of failure is very small.
* In order to encode a large number of possible messages *m*, we need a systematic way to generate points that are related to *m* in some way (like the x-coordinate has a simple relationship to the integer *m*).
### Discrete log on E
#### Discrete Log Problem
* Influence: upon it, we build the key-exchange protocols, the digital-signature schemes, and the public-key encryption systems
* Definition: with a finite cyclic group G = {g, g<sup>2</sup>, g<sup>3</sup>, ...} of prime order N, given (g, g<sup>x</sup>) ∈ G<sup>2</sup>, for an x sampled uniformly at random from Z<sub>N</sub>, find x ∈ Z<sub>N</sub>
* Hardness: depend crucially on the choice of the group G
  * for the additive group of integers modulo N, it could be solved in polynomial time
  * for the multiplicative group of integers modulo N, the best known algorithm takes sub-exponential time
  * for elliptic-curve groups (that your laptop uses to talk to your mail server), the best known algorithm requires exponential time O(N<sup>1/2</sup>)
#### Extension to E
* Definition: if E is an elliptic curve over F<sun>q</sub> and B is a point of E, then the discrete log problem on E (to the base B) is: given a point P ∈ E, of finding an integer x ∈ Z such that xB = P if such an integer x exists
* It seems that the analogous systems using elliptic curves defined over F<sub>2<sup>r</sup></sub> will be secure with significantly smaller values of r
* Practical reasons (relating to both hardware and software) prefer to do arithmetic over F<sub>2<sup>r</sup></sub>
  * it might be more convenient in applications than based on Discrete Log Problem in F<sub>q</sub><sup>*</sup>

## Questions
1. P163 - one possible probabilistic method -> why 30 to 50 are enough?
