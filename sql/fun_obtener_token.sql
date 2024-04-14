-- FUNCTION: public.fun_obtener_token(bigint, character varying)

-- DROP FUNCTION IF EXISTS public.fun_obtener_token(bigint, character varying);

CREATE OR REPLACE FUNCTION public.fun_obtener_token(
	bigint,
	character varying)
    RETURNS SETOF typ_token
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	lNumero		ALIAS FOR $1;
	cToken		ALIAS FOR $2;	
	
	Tokens      typ_token;
	recTokens	RECORD;
BEGIN
	FOR recTokens IN
		SELECT key_token, fec_expira FROM ctl_token_ia WHERE num_empleado = $1::bigint AND key_token = $2::character varying ORDER BY keyx DESC LIMIT 1
	LOOP
		Tokens.key_token 	:= recTokens.key_token;
		Tokens.fec_expira	:= recTokens.fec_expira;
		
		RETURN NEXT Tokens;
	END LOOP;
END
$BODY$;