uniform sampler2DRect src_tex_unit0;
uniform vec2 sampleDivisor;
uniform vec2 depthPoint;

vec2 samplePos;
float dist;
float newRad;
float newX;
float newY;

void main( void )
{
    
    vec2 st		= gl_TexCoord[0].st;

//    float maxX = depthPoint.x + 20.0;
//    float minX = depthPoint.x - 20.0;
//    
//    float maxY = depthPoint.y +  20.0;
//    float minY = depthPoint.y - 20.0;
    
//    
//    for(float i=0.;i<10.;i++){
//        vec2 max = depthPoint + vec2(20.*i);
//        vec2 min = depthPoint - vec2(20.*i);
//    	if( st.s >= min.x && st.s <= max.x && st.t >= min.y && st.t <= max.y){
//          //  vec2 divisor = sampleDivisor * 1.5;
//            //    float divisor1 = sampleDivisor.y * 1.5;
//            
//            samplePos = st.st - mod( st.st, vec2(10./i) );
//        }else{
//            samplePos = st.st;
//
//        }
//    }
    
    vec2 max = depthPoint + vec2(40.);
    vec2 min = depthPoint - vec2(40.);
	
	if( st.s >= min.x && st.s <= max.x && st.t >= min.y && st.t <= max.y){

//    vec2 divisor = sampleDivisor * 5.;
    
    float relX = st.s - depthPoint.x;
	float relY = st.t - depthPoint.y;
   
    float ang =  atan(relY, relX);
    dist = sqrt(relX*relX + relY*relY);
       
        if(dist <= 40.){
    newRad = dist * (dist/10. + 0.1);
    newX = depthPoint.x + cos( ang ) * newRad;
    newY = depthPoint.y + sin( ang ) * newRad;
        
//    float divisor1 = sampleDivisor.y * 1.5;

//      samplePos = st.st - mod( st.st, vec2(newX, newY) );
        samplePos = vec2(newX, newY);
        
    }else{
        samplePos = st;
//       samplePos = st.st - mod( st.st,  sampleDivisor);
//        gl_FragColor = texture2DRect(src_tex_unit0, st );

    }
    
    gl_FragColor = texture2DRect( src_tex_unit0, samplePos );

//	samplePos = gl_TexCoord[0].st - mod( gl_TexCoord[0].st, sampleDivisor );
//    * (vec4(1.0, 0.0, 0.0, 1.0) * sampleDivisor.x)
//    vec2(10.
    }else{
			//just draw the pixels as normal
			gl_FragColor = texture2DRect(src_tex_unit0, st );

}
}