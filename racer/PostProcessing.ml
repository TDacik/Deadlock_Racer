(* Postprocessing of data races based on detected imprecisions.
 *
 * Author: Tomas Dacik (idacik@fit.vut.cz), 2024 *)

open Imprecision

let run res =
  let filter =
    if RaceAnalysis.Result.is_race_free res then
      (function (FunctionPointer _ | Unlock _) -> true | _ -> false)
    else if RaceAnalysis.Result.has_must_race res then
      (function (FunctionPointer _ | Unlock _) -> false | _ -> true)
    else (fun _ -> true)
   in
   Imprecision.report filter
