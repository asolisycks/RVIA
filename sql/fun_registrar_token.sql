-- FUNCTION: public.fun_registrar_token(bigint, character varying, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_token(bigint, character varying, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_token(
	bigint,
	character varying,
	timestamp)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 	ALIAS FOR $1;
	sToken			ALIAS FOR $2;
	sExpira			ALIAS FOR $3;
BEGIN	
	
	INSERT INTO public.ctl_token_ia( num_empleado, key_token, fec_expira )
	VALUES ($1::bigint, $2::varchar, $3::timestamp);
	
	RETURN 1; --Inserto
	
END
$BODY$;

ALTER FUNCTION public.fun_registrar_token(bigint, character varying, timestamp)
    OWNER TO syscheckattendancebyface;
