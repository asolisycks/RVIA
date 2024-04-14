-- FUNCTION: public.fun_registrar_items_checkmarx(bigint, bigint, character varying, integer, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying)

-- DROP FUNCTION IF EXISTS public.fun_registrar_items_checkmarx(bigint, bigint, character varying, integer, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying, character varying);

CREATE OR REPLACE FUNCTION public.fun_registrar_items_checkmarx(
	bigint,
	bigint,
	character varying,
	integer,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying,
	character varying)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumEmpleado 			ALIAS FOR $1;
	lIDProyecto				ALIAS FOR $2;
	sProjectName			ALIAS FOR $3;
	iId						ALIAS FOR $4;
	dDetectionDate			ALIAS FOR $5;
	sDirectLink				ALIAS FOR $6;
	sQueryName				ALIAS FOR $7;
    sSourceFolder			ALIAS FOR $8;
	sSourceFilename			ALIAS FOR $9;
	sSourceLine				ALIAS FOR $10;
	sSourceObject			ALIAS FOR $11;
	sDestinationFolder		ALIAS FOR $12;
    sDestinationFilename	ALIAS FOR $13;
	sDestinationLine		ALIAS FOR $14;
	sDestinationObject		ALIAS FOR $15;
	sResultState			ALIAS FOR $16;
	sSeverity				ALIAS FOR $17;
    sResultSeverity			ALIAS FOR $18;
BEGIN	
	
	INSERT INTO public.tbl_registra_items_checkmarx( num_empleado, id_proyecto, nom_proyecto, num_id, fec_detection_date, rut_direct_link, fun_query_name, nom_source_folder, nom_source_filename, 
													 num_surce_line, nom_source_object, nom_destination_folder, nom_destination_filename, num_destination_line, nom_destination_object, nom_result_state, num_severity, nom_result_severity )
	VALUES ($1::bigint, $2::bigint, $3::varchar, $4::integer, $5::varchar, $6::varchar, $7::varchar, $8::varchar, $9::varchar, $10::varchar, $11::varchar, $12::varchar, $13::varchar, $14::varchar, $15::varchar, $16::varchar, $17::varchar, $18::varchar );
	
	RETURN 1; --Inserto
	
END
$BODY$;