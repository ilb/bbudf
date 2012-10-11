SET TERM ^ ;
execute block
returns(
	res varchar(500),
	errstr varchar(255)
)
as
declare variable filename varchar(100);
declare variable err integer;
begin
	filename=bbudf_tempnam(null,null);
	err=bbudf_file_put_contents(filename,cast('test1!' as blob),null,0);
	err=bbudf_file_put_contents(filename,cast('test2!' as blob),null,1);
	res=bbudf_file_get_contents(filename);
	errstr=bbudf_strerror(err);
	suspend;
end
^
SET TERM ; ^