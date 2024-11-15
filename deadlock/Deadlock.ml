(* DeadlockF : command-line options and logging utilities.
 *
 * Author: Tomas Dacik (idacik@fit.vut.cz), 2024 *)

let version = "2.0"

module Self = Plugin.Register
  (struct
    let name = "DeadlockF"
    let shortname = "deadlock"
    let help = "Deadlock detection"
  end)

include Self
include Print_utils.Make(Self)

module Enabled = False
  (struct
    let option_name = "-deadlock"
    let help = "Run deadlock detection"
  end)

module JsonOutput = Self.Filepath
  (struct
    let option_name = "-dl-json-output"
    let help = "Output summary of results in json"
    let arg_name = "json"
    let existence = Frama_c_kernel.Filepath.Must_not_exist
    let file_kind = "Result"
  end)
