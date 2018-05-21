---
usemathjax: true
excerpt: "Interview Cake Problem 24 - Product of Other Numbers"
---
---
#### *In this problem we are given an array $A$ of integers, and asked to return an array $O$ of the same size in which $O[i]$ contains the product of all elements in $A$ except $A[i]$ (Without using division).*

---


### Naive Solution
The problem states that we must not use division, which is understandable because otherwise we could trivially calculate the product once and then divide it by the value at each index to solve it -- in $O(n)$ time and $O(1)$ extra space. One could imagine the need for such an algorithm arising in the context of a microcontroller which has no divide capability.

Without division, a brute force implementation would be to calculate the product of all other numbers for each index, which would take $O(n^2)$ time and $O(1)$ space.  

### Optimal Solution
The first key observation from our naive solution is that many multiplications are repeated which could be reused between iterations. We will thus maintain an $n$-length additional array during the running of this algorithm - $M$ - for tracking and reusing intermediate products.

The second key observation is that - if we are careful in using the intermediate array - a symmetry arises which allows us to terminate in $O(n)$ time. When considering index $k$ we essentially want to combine two partial products: the product of elements to the left of $k$, and that of elements to the right of $k$.  We can pass down $M$ once incrementally calculating the product of all $n$ numbers, and then pass back up it once "dynamically" calculating the product of elements less than the current index.

#### Imperative Implementation (C++)
  ```cpp
  vector<int> getProductsOfAllIntsExceptAtIndex(const vector<int>& intVector)
  {
      vector<int> M(intVector);
      vector<int> O(intVector);
      int n = intVector.size();
      int pivot = 1;

      // corner cases
      if (n <= 1){
          throw std::length_error("input is too small.");
      }
      if (n == 2){
          O[0] = intVector[1];
          O[1] = intVector[0];
          return O;
      }
      if (n == 3){
          O[0] = intVector[1]*intVector[2];
          O[1] = intVector[0]*intVector[2];
          O[2] = intVector[0]*intVector[1];
          return O;
      }

      // first iteration fills M backwards
      for (int i = n - 2; i >= pivot; i--){
          M[i] = intVector[i] * M[i+1];
      }
      O[0] = M[pivot];

      // now dynamically fill the output and update M
      // left of pivot - product from A[0] upto A[pivot-1]
      // right of pivot - product from A[n-1] downto A[pivot+1]
      for (int i = pivot; i < n-1; i++){
          M[pivot] = M[pivot-1] * intVector[i];
          O[i] = M[pivot-1] * M[pivot+1];
          pivot++;
      }
      O[n-1] = M[pivot-1];

      return O;
  }
```
#### Functional Implementation (OCaml)
  ```ocaml
  exception List_Too_Small of int;;
  let prodOfOtherNums l =
      let n = List.length l in
      match l with
      (* Error Case *)
      | _ when n <= 1 -> raise (List_Too_Small n)
      (* Corner Cases *)
      | h::t when n == 2 -> (List.hd t)::(h::[])
      | f::(s::t) when n == 3 ->
              let a = s * List.hd t in
              let b = f * List.hd t in
              let c = (f * s)::[] in
              (a::(b::c))
      (* General Case *)
      | _ when n > 3 ->
              (* mult_up: consecutively multiply every element in list,
               * save intermediate products *)
              let rec mult_up m = function
                  | [] -> m
                  | h::t -> mult_up ((h * List.hd m)::m) t
              in
              (* In OCaml, we have imutable data,
               * so need two M arrays as oppsed to one in imperative languages *)
              let rl = List.rev l in
              let m_right = mult_up [List.hd rl] (List.tl rl) in
              let m_left = mult_up [List.hd l] (List.tl l) in
              (* Remove last 2 from M-left and first 2 from M-right
               * - instead of using indexing to calc O[i] = M[i-1] * M[i+1]
               * - this allows us to use recursion! *)
              let first = List.hd (List.tl m_right) in
              let last = (List.hd (List.tl m_left))::[] in
              let rec mult_pairs o = function
                  | ([],[]) -> List.rev o
                  | (h1::t1, h2::t2) -> mult_pairs ((h1 * h2)::o) (t1,t2)
              in
              let cut_two list = List.tl (List.tl list) in
              (* Tricky alignment, example below...
               * - input = [1,2,3,4,5]
               * - m_left =  [120, 24, 6, 2, 1] --truncated--> [6, 2, 1]
               * - m_right = [120,120,60,20, 5] --truncated--> [60,20,5]
               * - desired output = [120] @ [60 * 1, 20 * 2, 5 * 20] @ [24]
               * --> note that to attain the desired output, m_left must be reversed *)
              let middle = mult_pairs [] (List.rev (cut_two m_left), cut_two m_right) in
              (first::middle)@last;;
  ```
