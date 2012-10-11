SET TERM ^ ;
execute block
returns(
	res blob,
	code int
)
as
begin
select bbudf_curl_exec('GET','http://localhost',NULL,NULL,NULL,NULL,NULL,NULL) from rdb$database into res;
select bbudf_curl_get_response_code() from rdb$database into code;
suspend;
end
^
SET TERM ; ^
