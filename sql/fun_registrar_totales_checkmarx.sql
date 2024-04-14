-- FUNCTION: public.fun_registrar_totales_checkmarx(bigint, bigint, character varying, integer, integer, integer)

-- DROP FUNCTION IF EXISTS public.fun_registrar_totales_checkmarx(bigint, bigint, character varying, integer, integer, integer);

CREATE OR REPLACE FUNCTION public.fun_registrar_totales_checkmarx(
	bigint,
	bigint,
	character varying,
	integer,
	integer,
	integer)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado	ALIAS FOR $1;
	lIDProyecto		ALIAS FOR $2;
	sNomProyecto	ALIAS FOR $3;
	iNumHigh		ALIAS FOR $4;
	iNumMedium		ALIAS FOR $5;
	iNumLow			ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_totales_checkmarx( num_empleado, id_proyecto, nom_proyecto, num_high, num_medium, num_low )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::integer, $5::integer, $6::integer);
	
	RETURN 1; --Inserto
	
END
$BODY$;
