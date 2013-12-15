uniform sampler2DRect src_tex_unit0;
uniform vec2 src_tex_offset0;

uniform vec2 sampleDivisor;
uniform vec2 rectPos;

uniform float multiplier;


//need to replace radius with that increases the pixels near closestX,closestY by an amount that does not effect the other pixels

//uniform float minZoom;
//uniform float maxZoom;

vec4 color;

void main( void )

/*
 What I want is a multiplier effect, where the +/-20px near closestX,closestY are larger than that the other pixels. For ease, the whole pixelation is applied. Can this be?
 
 if((gl_TexCoord[0].s >=  || gl_TexCoord[0].s + 20 == closestX) && (gl_TexCoord[0].t - 20 == closestY || gl_TexCoord[0].t + 20 == closestY)){
    
    uniform float closeX = closestX * 1.5;
    uniform float closeY = closestY * 1.5;
 
 }

        vec2 samplePos = st - mod( st, sampleDivisor );
    
    //In the openFrameworks app
    shader.setUniform2f("sampleDivisor", point.x, point.y);
    shader.setUniform2f("rectPos", closePixel.x, closePixel.y);
    shader.setUniform1f("circleRadius", radius);
    shader.setUniform1f("minZoom", 0.1);
    shader.setUniform1f("maxZoom", 1);

 instead of drawing the pixels from the origin with the size determined by closestX & closestY, I am using the magnify effect, but drawing the pixels instead.
  
 this line is drawing the pixels every sampleDivisor using modulo; this is the pixelation part
 vec2 samplePos = gl_TexCoord[0].st - mod( gl_TexCoord[0].st, sampleDivisor );

 
 */

{
	
	vec2 st		= gl_TexCoord[0].st;
	
	//check if our pixels fit in the bounding rect - so we avoid expensive operations like sqrt.
	
//	float maxX = circlePos.x + circleRadius;
//	float minX = circlePos.x - circleRadius;
//	
//	float maxY = circlePos.y + circleRadius;
//	float minY = circlePos.y - circleRadius;
    
    float maxX = rectPos.x + 20;
    float minX = rectPos.x - 20;
    
    float maxY = rectPos.y +  20;
    float minY = rectPos.y - 20;
	
//	if( st.s > minX && st.s < maxX && st.t > minY && st.t < maxY){
	if( st.s >= minX && st.s <= maxX && st.t >= minY && st.t <= maxY){
	
        float nearX = st.x * 1.5;
		float relX = st.x - rectPos.x;
		float relY = st.y - rectPos.y;
		
//		float ang =  atan(relY, relX);
		float dist = sqrt(relX*relX + relY*relY);
		
		if( dist <= circleRadius ){
            
			//figure a zoom value for the pixel based on its distance from the center of the circle
			float newRad = dist * ( (maxZoom * dist/circleRadius) + minZoom );
            
			float newX = circlePos.x + cos( ang ) * newRad;
			float newY = circlePos.y + sin( ang ) * newRad;
            
			gl_FragColor = texture2DRect(src_tex_unit0, vec2(newX, newY) );
			
		}else{
			//just draw the pixels as normal
			gl_FragColor = texture2DRect(src_tex_unit0, st );
		}
		
	}else{
        //just draw the pixels as normal
        gl_FragColor = texture2DRect(src_tex_unit0, st );
	}
}