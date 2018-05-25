exception List_Too_Small of int;;
let highestProductOf3 listOfInts =
  let n = List.length listOfInts in
  match listOfInts with
  (* error case *)
  | _ when n < 3 -> raise (List_Too_Small n)
  (* Corner Case *)
  | f::(s::t) when n == 3 -> f * s * (List.hd t)
  (* General Case *)
  | a::(b::(c::tl)) when n > 3 ->
    (* The first 3 elements help to initialize the 5 parameters we keep track of *)
    let max a b =
      match (a > b) with
      | true -> a
      | false -> b in
    let min a b =
      match (a < b) with
      | true -> a
      | false -> b in
    let h3_init = a * b * c in
    let h2_init = max (max (a*b) (a*c)) (b*c) in
    let h_init = max (max a b) c in
    let l2_init = min (min (a*b) (a*c)) (b*c) in
    let l_init = min (min a b) c in
    let rec aux h3 h2 h l2 l = function
      | [] -> h3
      | head::tail ->
        match head with
        | head when head < 0 ->
          let hprod3 = max h3 (head * l2) in
          let hprod2 = max h2 (head * l) in
          let lprod2 = min l2 (head * h) in
          let highest = max h head in
          let lowest = min l head in
          aux hprod3 hprod2 highest lprod2 lowest tail
      | head when head > 0 ->
          let hprod3 = max h3 (head * h2) in
          let hprod2 = max h2 (head * h) in
          let lprod2 = min l2 (head * l) in
          let highest = max h head in
          let lowest = min l head in
          aux hprod3 hprod2 highest lprod2 lowest tail
    in
    aux h3_init h2_init h_init l2_init l_init tl;;

(* Test size 0 *)
try
  Printf.printf "%d " (highestProductOf3[]);
  Printf.printf "\n"
with
  List_Too_Small(_) -> Printf.printf "List is too small.\n";;

(* Test size 1 *)
try
  Printf.printf "%d " (highestProductOf3[1]);
  Printf.printf "\n"
with
  List_Too_Small(_) -> Printf.printf "List is too small.\n";;

(* Test size 2 *)
try
  Printf.printf "%d " (highestProductOf3[1;2]);
  Printf.printf "\n"
with
  List_Too_Small(_) -> Printf.printf "List is too small.\n";;

(* Test size 4 *)
Printf.printf "%d " (highestProductOf3[1;2;3;4]);;
Printf.printf "\n";;

(* Test longer list *)
Printf.printf "%d " (highestProductOf3[6;1;3;5;7;8;2]);;
Printf.printf "\n";;

(* Test List with 1 negative *)
Printf.printf "%d " (highestProductOf3[-5;4;8;2;3]);;
Printf.printf "\n";;

(* Test List with 2 negatives *)
Printf.printf "%d " (highestProductOf3[-10;1;3;2;-10]);;
Printf.printf "\n";;

(* Test List with all negatives *)
Printf.printf "%d " (highestProductOf3[-5;-1;-3;-2]);;
Printf.printf "\n";;
