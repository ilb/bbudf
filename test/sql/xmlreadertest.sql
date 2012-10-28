SET TERM ^ ;
execute block
RETURNS (
    NAME Varchar(128),
    LOCALNAME Varchar(128),
    VAL Varchar(8191),
    DEPTH Integer,
    NODETYPE Integer,
    ISEMPTYELEMENT Integer,
    entrykey Varchar(512) )
AS
DECLARE VARIABLE path varchar(300);
DECLARE VARIABLE reader int;
DECLARE VARIABLE res int;
BEGIN
  path='/tmp/xmlreadertest.xml';
  select BBUDF_XMLREADER_OPEN(:path) from RDB$DATABASE into reader;
  if (reader <> 0) then
  begin
    select BBUDF_XMLREADER_READ(:reader) from RDB$DATABASE into res;
    while (res=1) do
    begin

        select BBUDF_XMLREADER_NODETYPE(:reader) from RDB$DATABASE into nodetype;
        if (nodetype=1) then
        begin
            select
                BBUDF_XMLREADER_NAME(:reader),
                BBUDF_XMLREADER_LOCALNAME(:reader),
                BBUDF_XMLREADER_DEPTH(:reader),
                BBUDF_XMLREADER_ISEMPTYELEMENT(:reader),
                BBUDF_XMLREADER_GETATTRIBUTE(:reader,'key')
            from RDB$DATABASE into
                name,
                localname,
                depth,
                isemptyelement,
                entrykey;

            if (name='entry') then val=BBUDF_XMLREADER_READSTRING(:reader);
            else val=NULL;
            suspend;
        end
        select BBUDF_XMLREADER_READ(:reader) from RDB$DATABASE into res;
    end
    select BBUDF_XMLREADER_CLOSE(:reader) from RDB$DATABASE into res;
  end
END
^
SET TERM ; ^

