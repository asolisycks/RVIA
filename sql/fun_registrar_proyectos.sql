-- FUNCTION: public.fun_registrarproyectos_rv(bigint, character varying, character varying, date, date, bigint, smallint, character varying, character varying, numeric, numeric, integer)

-- DROP FUNCTION IF EXISTS public.fun_registrarproyectos_rv(bigint, character varying, character varying, date, date, bigint, smallint, character varying, character varying, numeric, numeric, integer);

CREATE OR REPLACE FUNCTION public.fun_registrarproyectos_rv(
	bigint,
	character varying,
	character varying,
	date,
	date)
    RETURNS smallint
    LANGUAGE 'plpgsql'
    COST 100
    VOLATILE PARALLEL UNSAFE
AS $BODY$

DECLARE
	lNumGerente			ALIAS FOR $1;
	cNomProyecto		ALIAS FOR $2;
	cDescProyecto		ALIAS FOR $3;
	cFechaInicio		ALIAS FOR $4;
	cFecPromesa			ALIAS FOR $5;
	
	cNomGerente 	CHAR(60); 		-- Sale de la tabla cat_gerentes
	lNumCoordinador BIGINT = 0;		-- Sale de la tabla cat_colaboradores
	cNomCoordinador CHAR(60);		-- Sale de la tabla cat_coordinadores
	lNumNacional 	BIGINT = 0;		-- Sale de la tabla cat_nacionales según el número del coordinador
	cNomNacional 	CHAR(60);		-- Sale de la tabla cat_nacionales según el número del coordinador
BEGIN	
	-- ctl_proyectos
	-- Obetener nombre del gerente
	SELECT BTRIM(nom_gerente) INTO cNomGerente FROM cat_gerentes WHERE num_gerente = lNumGerente;
	IF NOT FOUND THEN
		-- RAISE NOTICE 'No cNomGerente at : %.', cNomGerente;
		RETURN -1; -- No existe el gerente registrado
	ELSE
		RAISE NOTICE 'No Gerente at : %.', lNumGerente;
		--SELECT num_coordinador FROM cat_colaboradores WHERE num_gerente = 90329121 LIMIT 1;
		SELECT num_coordinador INTO lNumCoordinador FROM cat_colaboradores WHERE num_gerente = lNumGerente LIMIT 1;
		IF NOT FOUND THEN
			RAISE NOTICE 'No coordinador at : %', lNumCoordinador;
			RETURN -2; -- No existe el  nombre del colaborador registrado			
		ELSE			
			SELECT BTRIM(nom_coordinador) INTO cNomCoordinador FROM cat_coordinadores WHERE num_coordinador = lNumCoordinador;			
			IF NOT FOUND THEN
				-- RAISE NOTICE 'No Coord at : %', cNomCoordinador;
				RETURN -3; -- No existe el nombre del coordinador registrado								
			ELSE
				RAISE NOTICE 'No lNumCoordinador at : %.', lNumCoordinador;
				IF lNumCoordinador = 91080819 OR lNumCoordinador = 91452716 THEN -- Coordinación 3
					lNumNacional := 90203224;
					cNomNacional :=	'HECTOR ANTONIO CRUZ ZAZUETA';
				END IF;
				IF lNumCoordinador = 90035135 OR lNumCoordinador = 90035313	THEN -- Coordinación 1
					lNumNacional := 96652551;
					cNomNacional :=	'TERESA GUADALUPE GALVEZ GASTELUM';
				END IF;
				-- SELECT fun_registrarproyectos( '90329121'::BIGINT, 'DEDEDEDEDE'::VARCHAR, 'DEDEDEDDAADASDAFSDFSDF FSDFSDFSDFSDF'::VARCHAR, '2023-03-20'::DATE, '2023-03-20'::DATE );
				RAISE NOTICE 'No lNumNacional-cNomNacional at : %-%', lNumNacional, cNomNacional;
				IF NOT EXISTS ( SELECT BTRIM(nom_proyecto) FROM ctl_proyectos WHERE num_colaborador = $6::bigint AND nom_proyecto = $2 ) THEN
					INSERT INTO public.ctl_proyectos_rv( num_gerente, nom_gerente, nom_proyecto, des_proyecto, num_coordinador, nom_coordinador, 
						num_nacional, nom_nacional, fec_inicio, fec_promesa)
					VALUES ($1::bigint, cNomGerente::varchar, $2::varchar, $3::varchar, lNumCoordinador::bigint, cNomCoordinador::varchar, 
							lNumNacional::bigint, cNomNacional::varchar, $4::date, $5::date);
					RETURN 1; --Inserto
				ELSE
					-- RAISE NOTICE 'El proyecto ya está registrado para este colaborador: %', $2;
					RETURN -4;  -- El proyecto ya está registrado para este colaborador.									
				END IF;
			END IF;
		END IF;
	END IF;
END
$BODY$;
