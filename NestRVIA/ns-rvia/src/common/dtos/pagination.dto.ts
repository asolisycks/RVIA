import { Type } from "class-transformer";
import { IsOptional, IsPositive, Min } from "class-validator";

export class PaginationDto
{
    @IsOptional()
    @IsPositive()
    //Transformar
    @Type( () => Number) // Esto es lo mismo que enableImplicitConversions: true
    limit?: number;

    @IsOptional()
    //@IsPositive()
    @Min(0)
    @Type( () => Number) // Esto es lo mismo que enableImplicitConversions: true
    offset?: number;

}