SET TERM ^ ;
execute block
returns(
	errstr varchar(255)
)
as
declare variable err integer;
begin
	errstr=bbudf_strerror(2);
	suspend;

end
^
SET TERM ; ^