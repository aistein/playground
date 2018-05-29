let mergingRanges meetings =
  (* pair of tail-recursive functions for insertion sort *)
  let rec start_sort = function
    | [] -> []
    | x::l -> insert x (start_sort l)
  and insert mtg = function
    | [] -> [mtg]
    | x::l -> if (fst mtg) < (fst x) then mtg :: x :: l
      else x :: mtg :: l
  in
  let meetings = start_sort meetings in
  let rec aux merged_mtgs = function
    | [] -> merged_mtgs
    | h::tl ->
      let a = List.hd merged_mtgs in
      let a_st = fst a in
      let a_fin = snd a in
      let b_st = fst h in
      let b_fin = snd h in
      if (a_st <= b_st && a_fin >= b_fin) then aux merged_mtgs tl
      else if a_fin >= b_st then aux ((a_st, b_fin)::(List.tl merged_mtgs)) tl
      else aux (h::merged_mtgs) tl
  in
  aux [(List.hd meetings)] (List.tl meetings);;

let pp_int_pair ppf (x,y) =
  Printf.fprintf ppf "(%d,%d)" x y;;

(* Test meetings overlap *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(1,3);(2,4)]);
Printf.printf "\n";;

(* Test meetings touch *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(5,6);(6,8)]);
Printf.printf "\n";;

(* Test meeting contains other meeting *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(1,8);(2,5)]);;
Printf.printf "\n";;

(* Test meetings stay separate *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(1,3);(4,8)]);;
Printf.printf "\n";;

(* Test multiple merged meetings *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(1,4);(2,5);(5,8)]);;
Printf.printf "\n";;

(* Test meetings not sorted *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(5,8);(1,4);(6,8)]);;
Printf.printf "\n";;

(* Test sample input *)
List.iter (Printf.printf "%a " pp_int_pair) (mergingRanges [(0,1);(3,5);(4,8);(10,12);(9,10)]);;
Printf.printf "\n";;
