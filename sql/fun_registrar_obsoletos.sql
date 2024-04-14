-- FUNCTION: public.fun_registrar_obsoletos(bigint, bigint, character varying, character varying, integer, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_obsoletos(bigint, bigint, character varying, character varying, integer, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_obsoletos(
	bigint,
	bigint,
	character varying,
	character varying,
	integer,
	character varying)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 	ALIAS FOR $1;
	lIdProyecto		ALIAS FOR $2;
	sProyecto		ALIAS FOR $3;
	sArchivo		ALIAS FOR $4;
	iLinea			ALIAS FOR $5;
	sSentencia		ALIAS FOR $6;
BEGIN	
	
	INSERT INTO public.tbl_registra_obsoletos_ia( num_empleado, id_proyecto, nom_proyecto, nom_archivo, num_linea, dat_obsoleto )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::varchar);
	
	RETURN 1; --Inserto
	
END
$BODY$;