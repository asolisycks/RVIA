-- FUNCTION: public.fun_registrar_totales_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer)

-- DROP FUNCTION IF EXISTS public.fun_registrar_totales_proyecto(bigint, bigint, character varying, character varying, integer, integer, integer, integer);

--

CREATE OR REPLACE FUNCTION public.fun_registrar_totales_proyecto(
	bigint,
	bigint,
	character varying,
	character varying,
	integer,
	integer,
	integer,
	integer)
    
	RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	
	lEmpleado 		ALIAS FOR $1;
	lIdpproyecto 	ALIAS FOR $2;
	sNomProyecto 	ALIAS FOR $3;
	sNomLenguaje 	ALIAS FOR $4;
	iNumFiles		ALIAS FOR $5;
	iNumBlank		ALIAS FOR $6;
	iNumComment		ALIAS FOR $7;
	iNumCode		ALIAS FOR $8;
	
BEGIN	
		
	INSERT INTO public.tbl_registra_totales( num_empleado, id_proyecto, nom_proyecto, nom_language, num_files, num_blank, num_comment, num_code )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::varchar, $5::integer, $6::integer, $7::integer, $8::integer );
	
	RETURN 1; --Inserto
	
END
$BODY$;
