bbudf
=====

Firebird udf wrapper functions (curl,libxml2,etc).

This library can be used in legacy firebird applications
to execute external transaction or get some data for processing.

Binaries
https://build.opensuse.org/package/show/home:slavb18:firebird/bbudf

Example use: call web service using curl and parse xml response with XML Reader.
```
execute block
RETURNS (
    Currency Varchar(3),
    Rate numeric(10,8)
)
AS
DECLARE VARIABLE url varchar(300);
DECLARE VARIABLE reader int;
DECLARE VARIABLE res int;
DECLARE VARIABLE xml blob;
BEGIN
  url='http://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml';
  xml=bbudf_curl_exec('GET',url,NULL,NULL,NULL,NULL,NULL,NULL);
  res=bbudf_curl_get_response_code();
  if(res!=200) then  exception;

  reader=bbudf_xmlreader_openblob(:xml);
  if (reader != 0) then
  begin
    while (BBUDF_XMLREADER_READ(:reader)=1) do
    begin
        if (BBUDF_XMLREADER_NODETYPE(:reader)=1) then
        begin
                if (BBUDF_XMLREADER_LOCALNAME(:reader)='Cube') then
                begin
                   Currency=BBUDF_XMLREADER_GETATTRIBUTE(:reader,'currency');
                   Rate=BBUDF_XMLREADER_GETATTRIBUTE(:reader,'rate');
                   if (Currency is not null and rate is not null) then suspend;
                end
        end
    end
    BBUDF_XMLREADER_CLOSE(:reader);
  end
END
```
#How to build using cross-compilation on opensuse

1. install mingw32 packages sudo zypper install mingw32-cross-gcc mingw32-cross-gcc-c++ mingw32-gcc  mingw32-curl  mingw32-libxml2-2  mingw32-libxml2-devel mingw32-libcurl-devel
2. compile: make CONF=Release-cross-mingw32 (or use netbeans)