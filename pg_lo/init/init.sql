CREATE TABLE messages(id INT PRIMARY KEY, msg TEXT, img_oid OID);

CREATE ROLE cyhub;

GRANT USAGE ON SCHEMA public TO app_user;
GRANT USAGE ON SCHEMA public TO cyhub;
GRANT CREATE ON SCHEMA public TO cyhub;

GRANT ALL PRIVILEGES ON TABLE public.messages TO cyhub;
GRANT EXECUTE ON FUNCTION pg_catalog.lo_from_bytea(OID, bytea) TO cyhub;
GRANT EXECUTE ON FUNCTION pg_catalog.lo_import(TEXT, OID) TO cyhub;
GRANT EXECUTE ON FUNCTION pg_catalog.lo_export(OID, TEXT) TO cyhub;

SET ROLE cyhub;

DO $$
BEGIN
    PERFORM lo_import('/images/flag.png', 1337);
    PERFORM lo_import('/images/1.png', 1);
    PERFORM lo_import('/images/2.png', 2);
    PERFORM lo_import('/images/3.png', 3);
    INSERT INTO messages(id, msg, img_oid) VALUES 
        (1, 'First Image', 1),
        (2, 'Second Image', 2),
        (3, 'Third Image', 3),
        (1337, 'Check this 1337 image!', 1337);
END $$;

CREATE OR REPLACE FUNCTION get_message(p_id TEXT) RETURNS TEXT AS $$
DECLARE
    result TEXT;
BEGIN
    EXECUTE format('SELECT encode(lo_get(messages.img_oid), ''base64'') as img FROM messages WHERE id=%s::INT', p_id) INTO result;
    RETURN result;
END;
$$ LANGUAGE plpgsql SECURITY DEFINER;

CREATE OR REPLACE FUNCTION get_messages() RETURNS TABLE (id INT, msg TEXT, img TEXT) AS $$
DECLARE
    query TEXT;
BEGIN
    RETURN QUERY
    SELECT messages.id, messages.msg, encode(lo_get(messages.img_oid), 'base64') as img 
    FROM messages;
END;
$$ LANGUAGE plpgsql SECURITY DEFINER;

RESET ROLE;

GRANT EXECUTE ON FUNCTION get_message(TEXT) TO app_user;
GRANT EXECUTE ON FUNCTION get_messages() TO app_user;
