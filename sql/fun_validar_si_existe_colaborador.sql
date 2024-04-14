-- FUNCTION: public.fun_validar_si_existe_colaborador(bigint)

-- DROP FUNCTION IF EXISTS public.fun_validar_si_existe_colaborador(bigint);

CREATE OR REPLACE FUNCTION public.fun_validar_si_existe_colaborador(
	bigint)
    RETURNS SETOF bigint 
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
    ROWS 1000

AS $BODY$

DECLARE
	lNumero			ALIAS FOR $1;
BEGIN

	RETURN QUERY SELECT num_gerente FROM cat_gerentes WHERE num_gerente = $1::bigint;
	
	IF NOT FOUND THEN
	--	RAISE EXCEPTION 'No name at %.', $1;
		RETURN QUERY SELECT num_coordinador FROM cat_coordinadores WHERE num_coordinador = $1::bigint;
		
		IF NOT FOUND THEN
			
			RETURN QUERY SELECT num_nacional FROM cat_nacionales WHERE num_nacional = $1::bigint;	
			
			IF NOT FOUND THEN
				RETURN QUERY SELECT num_colaborador FROM cat_colaboradores WHERE num_colaborador = $1::bigint;	
			END IF;
		
		END IF;
		
	END IF;
	
	RETURN;
END
$BODY$;