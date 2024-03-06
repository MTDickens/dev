let read file =
  let chan = open_in file in
(* finalization code *)
  let finalize () = close_in chan in
  try
let nbytes = in_channel_length chan in
    let string = Bytes.create nbytes in
really_input chan string 0 nbytes;
            finalize();;
        string
  with exn ->
    (* finalize channel *)
    finalize ();
    (* re-raise exception *)
    raise exn;;