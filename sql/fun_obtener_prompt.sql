-- FUNCTION: public.fun_obtener_prompt(character, character, character)

-- DROP FUNCTION IF EXISTS public.fun_obtener_prompt(character, character, character);
-- SELECT * FROM ctl_prompt;
-- SELECT pmt_texto FROM ctl_prompt WHERE nom_cliente_ia = 'BITO' AND ext_lenguaje = 'PHP' AND nom_model = 'ADVANCED' AND flg_activo = 0;
-- SELECT fun_obtener_prompt('BITO', 'PHP', 'ADVANCED');


CREATE OR REPLACE FUNCTION public.fun_obtener_prompt(
	character,
	character,
	character)
    RETURNS SETOF character varying 
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	cNomCliente		ALIAS FOR $1;
	cLenguaje		ALIAS FOR $2;
	cModel			ALIAS FOR $3;
	
	Tokens      typ_token;
	recTokens	RECORD;
BEGIN

	RETURN QUERY SELECT pmt_texto FROM ctl_prompt WHERE nom_cliente_ia = $1 AND ext_lenguaje = $2 AND nom_model = $3 AND flg_activo = 0;
	
	--IF NOT FOUND THEN
	--	RAISE EXCEPTION 'No name at %.', $1;
	--END IF;
	
	RETURN;
END
$BODY$;

ALTER FUNCTION public.fun_obtener_prompt(character, character, character)
    OWNER TO syscheckattendancebyface;
